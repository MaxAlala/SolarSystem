package ru.javabegin.training.spring.dao.impls;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import javax.sql.DataSource;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BatchPreparedStatementSetter;
import org.springframework.jdbc.core.ResultSetExtractor;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.jdbc.core.namedparam.MapSqlParameterSource;
import org.springframework.jdbc.core.namedparam.NamedParameterJdbcTemplate;
import org.springframework.jdbc.core.namedparam.SqlParameterSource;
import org.springframework.jdbc.core.namedparam.SqlParameterSourceUtils;
import org.springframework.jdbc.core.simple.SimpleJdbcInsert;
import org.springframework.stereotype.Component;

import ru.javabegin.training.spring.dao.interfaces.MP3Dao;
import ru.javabegin.training.spring.dao.objects.MP3;

@Component("sqliteDAO")
public class SQLiteDAO implements MP3Dao {

	private SimpleJdbcInsert insertMP3;

	private NamedParameterJdbcTemplate jdbcTemplate;

	private DataSource dataSource;

	@Autowired
	public void setDataSource(DataSource dataSource) {
		this.jdbcTemplate = new NamedParameterJdbcTemplate(dataSource);
		this.insertMP3 = new SimpleJdbcInsert(dataSource).withTableName("mp3").usingColumns("name", "author");
		this.dataSource = dataSource;
	}

	@Override
	public int insert(MP3 mp3) {

		MapSqlParameterSource params = new MapSqlParameterSource();
		params.addValue("name", mp3.getName());
		params.addValue("author", mp3.getAuthor());

		return insertMP3.execute(params);

	}
	
//	 public int[] batchUpdate(final List<MP3> mp3) {
//	        int[] updateCounts = jdbcTemplate.batchUpdate("update mp3 set name = ?,last_name = ? where id = ?",
//	            new BatchPreparedStatementSetter() {
//	                public void setValues(PreparedStatement ps, int i) throws SQLException {
//	                        ps.setString(3, mp3.get(i).getName());
//	                        ps.setString(2, mp3.get(i).getAuthor());
//	                        ps.setInt(1, mp3.get(i).getId());
//	                    }
//	                
//	                    public int getBatchSize() {
//	                        return mp3.size();
//	                    }
//	                });
//	        
//	        return updateCounts;
//	    }
	
	 public int[] batchUpdate(final List<MP3> actors) {
	        SqlParameterSource[] batch =
	 SqlParameterSourceUtils.createBatch(actors.toArray());
	        int[] updateCounts = jdbcTemplate.batchUpdate(
	        		"update mp3 set name = :name, author = :author where id = :id", batch);
	        return updateCounts;
	    }
	 
	 

	@Override
	public int insertList(List<MP3> listMP3) {
		String sql = "insert into mp3 (author, name) VALUES (:author, :name)";

		SqlParameterSource[] params = new SqlParameterSource[listMP3.size()];

		int i = 0;

		for (MP3 mp3 : listMP3) {
			MapSqlParameterSource p = new MapSqlParameterSource();
			p.addValue("name", mp3.getName());
			p.addValue("author", mp3.getAuthor());

			params[i] = p;
			i++;
		}

		// SqlParameterSource[] batch =
		// SqlParameterSourceUtils.createBatch(listMP3.toArray());
		int[] updateCounts = jdbcTemplate.batchUpdate(sql, params);
		return updateCounts.length;
	}

	@Override
	public Map<String, Integer> getStat() {
		String sql = "select author, count(*) as count from mp3 group by author";

		return jdbcTemplate.query(sql, new ResultSetExtractor<Map<String, Integer>>() {

			public Map<String, Integer> extractData(ResultSet rs) throws SQLException {
				Map<String, Integer> map = new TreeMap<>();
				while (rs.next()) {
					String author = rs.getString("author");
					int count = rs.getInt("count");
					map.put(author, count);
				}
				return map;
			};

		});

	}

	@Override
	public void delete(int id) {
		String sql = "delete from mp3 where id=:id";

		MapSqlParameterSource params = new MapSqlParameterSource();
		params.addValue("id", id);

		jdbcTemplate.update(sql, params);
	}

	@Override
	public void delete(MP3 mp3) {
		delete(mp3.getId());
	}

	@Override
	public MP3 getMP3ByID(int id) {
		String sql = "select * from mp3 where id=:id";

		MapSqlParameterSource params = new MapSqlParameterSource();
		params.addValue("id", id);

		return jdbcTemplate.queryForObject(sql, params, new MP3RowMapper());
	}

	@Override
	public List<MP3> getMP3ListByName(String name) {
		String sql = "select * from mp3 where upper(name) like :name";

		MapSqlParameterSource params = new MapSqlParameterSource();
		params.addValue("name", "%" + name.toUpperCase() + "%");

		return jdbcTemplate.query(sql, params, new MP3RowMapper());
	}

	@Override
	public List<MP3> getMP3ListByAuthor(String author) {
		String sql = "select * from mp3 where upper(author) like :author";

		MapSqlParameterSource params = new MapSqlParameterSource();
		params.addValue("author", "%" + author.toUpperCase() + "%");

		return jdbcTemplate.query(sql, params, new MP3RowMapper());
	}

	@Override
	public int getMP3Count() {
		String sql = "select count(*) from mp3";
		return jdbcTemplate.getJdbcOperations().queryForObject(sql, Integer.class);
	}

	private static final class MP3RowMapper implements RowMapper<MP3> {

		@Override
		public MP3 mapRow(ResultSet rs, int rowNum) throws SQLException {
			MP3 mp3 = new MP3();
			mp3.setId(rs.getInt("id"));
			mp3.setName(rs.getString("name"));
			mp3.setAuthor(rs.getString("author"));
			return mp3;
		}

	}

}

package ru.javabegin.training.spring.dao.impls;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import javax.sql.DataSource;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.ResultSetExtractor;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.jdbc.core.namedparam.MapSqlParameterSource;
import org.springframework.jdbc.core.namedparam.NamedParameterJdbcTemplate;
import org.springframework.jdbc.support.GeneratedKeyHolder;
import org.springframework.jdbc.support.KeyHolder;
import org.springframework.stereotype.Component;
import org.springframework.transaction.annotation.Transactional;

import ru.javabegin.training.spring.dao.interfaces.MP3Dao;
import ru.javabegin.training.spring.dao.objects.Author;
import ru.javabegin.training.spring.dao.objects.MP3;

@Component("sqliteDAO")
public class SQLiteDAO implements MP3Dao {

	private static final String mp3Table = "mp3";
	private static final String mp3View = "mp3_view";

	private NamedParameterJdbcTemplate jdbcTemplate;

	@Autowired
	public void setDataSource(DataSource dataSource) {
		this.jdbcTemplate = new NamedParameterJdbcTemplate(dataSource);
	}

	@Override
	@Transactional
	public int insert(MP3 mp3) {

		String sqlInsertAuthor = "insert into author (name) VALUES (:authorName)";

		Author author = mp3.getAuthor();

		MapSqlParameterSource params = new MapSqlParameterSource();
		params.addValue("authorName", author.getName());

		KeyHolder keyHolder = new GeneratedKeyHolder();

		jdbcTemplate.update(sqlInsertAuthor, params, keyHolder);

		int author_id = keyHolder.getKey().intValue();

		// неверное имя поля author_id2
		String sqlInsertMP3 = "insert into mp3 (author_id2, name) VALUES (:authorId, :mp3Name)";

		params = new MapSqlParameterSource();
		params.addValue("mp3Name", mp3.getName());
		params.addValue("authorId", author_id);

		return jdbcTemplate.update(sqlInsertMP3, params);

	}

	@Override
	public int insertList(List<MP3> listMP3) {
		// String sql =
		// "insert into mp3 (name, author) VALUES (:author, :name)";
		//
		// SqlParameterSource[] params = new SqlParameterSource[listMP3.size()];
		//
		// int i = 0;
		//
		// for (MP3 mp3 : listMP3) {
		// MapSqlParameterSource p = new MapSqlParameterSource();
		// p.addValue("name", mp3.getName());
		// p.addValue("author", mp3.getAuthor());
		//
		// params[i] = p;
		// i++;
		// }
		//
		// // SqlParameterSource[] batch =
		// // SqlParameterSourceUtils.createBatch(listMP3.toArray());
		// int[] updateCounts = jdbcTemplate.batchUpdate(sql, params);
		// return updateCounts.length;

		int i = 0;

		for (MP3 mp3 : listMP3) {
			insert(mp3);
			i++;
		}

		return i;

	}

	@Override
	public Map<String, Integer> getStat() {
		String sql = "select author_name, count(*) as count from " + mp3View + " group by author_name";

		return jdbcTemplate.query(sql, new ResultSetExtractor<Map<String, Integer>>() {

			public Map<String, Integer> extractData(ResultSet rs) throws SQLException {
				Map<String, Integer> map = new TreeMap<>();
				while (rs.next()) {
					String author = rs.getString("author_name");
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
		String sql = "select * from " + mp3View + " where mp3_id=:mp3_id";

		MapSqlParameterSource params = new MapSqlParameterSource();
		params.addValue("mp3_id", id);

		return jdbcTemplate.queryForObject(sql, params, new MP3RowMapper());
	}

	@Override
	public List<MP3> getMP3ListByName(String mp3Name) {
		String sql = "select * from " + mp3View + " where upper(mp3_name) like :mp3_name";

		MapSqlParameterSource params = new MapSqlParameterSource();
		params.addValue("mp3_name", "%" + mp3Name.toUpperCase() + "%");

		return jdbcTemplate.query(sql, params, new MP3RowMapper());
	}

	@Override
	public List<MP3> getMP3ListByAuthor(String author) {
		String sql = "select * from " + mp3View + " where upper(author_name) like :author_name";

		MapSqlParameterSource params = new MapSqlParameterSource();
		params.addValue("author_name", "%" + author.toUpperCase() + "%");

		return jdbcTemplate.query(sql, params, new MP3RowMapper());
	}

	@Override
	public int getMP3Count() {
		String sql = "select count(*) from " + mp3Table;
		return jdbcTemplate.getJdbcOperations().queryForObject(sql, Integer.class);
	}

	private static final class MP3RowMapper implements RowMapper<MP3> {

		@Override
		public MP3 mapRow(ResultSet rs, int rowNum) throws SQLException {
			Author author = new Author();
			author.setId(rs.getInt("author_id"));
			author.setName("author_name");

			MP3 mp3 = new MP3();
			mp3.setId(rs.getInt("mp3_id"));
			mp3.setName(rs.getString("mp3_name"));
			mp3.setAuthor(author);
			return mp3;
		}

	}

}
